open ReasonJs;

open Utils;

type state = {
  topstories: StoryData.topstories,
  page: int,
  loading: bool
};

let component = ReasonReact.statefulComponent "TopStoriesPage";

let make _children => {
  let nearTheBottom () => distanceFromBottom () < 100;
  let handleLoaded (page, data) {ReasonReact.state} => {
    let updatedTopstories = Array.concat [state.topstories, data];
    ReasonReact.Update {topstories: updatedTopstories, page: page + 1, loading: false}
  };
  let loadNextPage self => {
    let {ReasonReact.state} = self;
    if (state.page < 4) {
      StoryData.fetchTopStories state.page (self.update handleLoaded) |> ignore;
      ReasonReact.Update {...state, loading: true}
    } else {
      ReasonReact.NoUpdate;
    };
  };
  let handleScroll _ self => {
    let {ReasonReact.state} = self;
    if (nearTheBottom () && not state.loading) {
      loadNextPage self
    } else {
      ReasonReact.NoUpdate;
    };
  };

  {
    ...component,
    initialState: fun () :state => {topstories: [||], page: 0, loading: false},

    didMount: fun self => {
      Dom.(Window.addEventListener "scroll" (self.update handleScroll) window);
      loadNextPage self
    },
    render: fun self => {
      let storyArray =
        if (Array.length self.state.topstories > 0) {
          Array.mapi
            (fun index story => <StoryListItem key=(string_of_int index) index story />)
            self.state.topstories
        } else {
          [||]
        };
      <div> (ReasonReact.arrayToElement storyArray) </div>
    }
  }
};
