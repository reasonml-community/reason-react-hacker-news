open Utils;

let styles = requireCSSModule("src/List.module.css");

type state = {
  stories: HackerNews.stories,
  storyType: string,
  page: int,
  loading: bool
};

type action =
  | Load(int)
  | Loaded((int, HackerNews.stories))
  | Loading;
  /* | Error; */

let component = ReasonReact.reducerComponent("List");
let make = (~max, ~page, ~storyType, _children) => {

  let itemsPerPage = 30;
  let loadPage = ({ReasonReact.reduce}, storyType, page) => {
      HackerNews.fetchStories(storyType, page, reduce(payload => Loaded(payload))) |> ignore;
      reduce(() => Loading, ());
    };

  {
    ...component,

    initialState: () => {
      stories: [||],
      page,
      storyType,
      loading: false
    },

    reducer: (action, state) =>
      switch action {
      | Loading =>
        ReasonReact.Update({
          ...state,
          loading: true,
          stories: [||]
        })

      | Loaded((page, data)) =>
        ReasonReact.Update({
          ...state,
          stories: data,
          page: page,
          loading: false
        })

      | Load(page) =>
        ReasonReact.SideEffects(self =>
          if (!self.state.loading) {
            loadPage(self, storyType, page);
          }
        )
      },

    didMount: (self) => {
      loadPage(self, storyType, page);
      ReasonReact.NoUpdate
    },

    willReceiveProps: (self) => {
      loadPage(self, storyType, page);
      {
        ...self.state,
        page,
        storyType
      }
    },

    render: (self) => {
      <div>
        <Header pageType={storyType} />
        <Pagination storyType maxPages={max} page={page} />
        <main className={classNameFilter(styles, [|("list", true), ("mainView", true), ("viewHasHeader", true)|])}>
          (
            if (Array.length(self.state.stories) > 0) {
              self.state.stories
              |> Array.mapi((index, story) =>
                <ListItem key=(string_of_int(index)) index={string_of_int(index+(page-1)*itemsPerPage+1)} story />)
              |> arrayEl
            } else {
              ReasonReact.nullElement
            }
          )
        </main>
      </div>
    }
  }
};
