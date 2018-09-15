open Belt;

open Utils;

type state = {
  topstories: StoryData.topstories,
  page: int,
  loading: bool,
  error: bool,
};

type action =
  | Loaded((int, StoryData.topstories))
  | Error
  | Loading
  | Scroll;

let component = ReasonReact.reducerComponent("TopStoriesPage");

let make = _children => {
  let nearTheBottom = () => distanceFromBottom() < 100;
  let loadNextPage = ({ReasonReact.state, send}) =>
    if (state.page < 4) {
      StoryData.fetchTopStories(state.page, result =>
        switch (result) {
        | Success(page, stories) => send(Loaded((page, stories)))
        | Error => send(Error)
        }
      )
      |> ignore;
      send(Loading);
    };
  {
    ...component,
    initialState: () => {
      topstories: [||],
      page: 0,
      loading: false,
      error: false,
    },
    reducer: (action, state) =>
      switch (action) {
      | Loading => ReasonReact.Update({...state, loading: true, error: false})
      | Loaded((page, data)) =>
        let updatedTopstories = Array.concat(state.topstories, data);
        ReasonReact.Update({
          ...state,
          topstories: updatedTopstories,
          page: page + 1,
          loading: false,
        });
      | Error => ReasonReact.Update({...state, loading: false, error: true})
      | Scroll =>
        ReasonReact.SideEffects(
          (
            self =>
              if (nearTheBottom() && ! self.state.loading) {
                loadNextPage(self);
              }
          ),
        )
      },
    didMount: self => {
      Webapi.Dom.(
        Window.addEventListener("scroll", _ => self.send(Scroll), window)
      );
      loadNextPage(self);
    },
    render: self =>
      <div>
        (
          self.state.error ?
            <div className="message">
              (ReasonReact.string("Something went wrong..."))
            </div> :
            ReasonReact.null
        )
        (
          self.state.loading ?
            <div className="error">
              (ReasonReact.string("Loading..."))
            </div> :
            ReasonReact.null
        )
        (
          if (Array.length(self.state.topstories) > 0) {
            self.state.topstories
            |. Array.mapWithIndex((index, story)
                 /* key must be a unique string attached to the story, DO NOT use index */
                 =>
                   <StoryListItem key=(string_of_int(story.id)) index story />
                 )
            |. ReasonReact.array;
          } else {
            ReasonReact.null;
          }
        )
      </div>,
  };
};